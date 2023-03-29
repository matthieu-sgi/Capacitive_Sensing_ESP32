# SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: CC0-1.0

import contextlib
import logging
import os
import socket
import time
from multiprocessing import Pipe, Process, connection
from typing import Iterator

import pytest
from pytest_embedded import Dut
from scapy.all import Ether, raw

ETH_TYPE = 0x2222


class EthTestIntf(object):
    def __init__(self, eth_type: int, my_if: str = ''):
        self.target_if = ''
        self.eth_type = eth_type
        self.find_target_if(my_if)

    def find_target_if(self, my_if: str = '') -> None:
        # try to determine which interface to use
        netifs = os.listdir('/sys/class/net/')
        logging.info('detected interfaces: %s', str(netifs))

        for netif in netifs:
            # if no interface defined, try to find it automatically
            if my_if == '':
                if netif.find('eth') == 0 or netif.find('enp') == 0 or netif.find('eno') == 0:
                    self.target_if = netif
                    break
            else:
                if netif.find(my_if) == 0:
                    self.target_if = my_if
                    break
        if self.target_if == '':
            raise Exception('network interface not found')
        logging.info('Use %s for testing', self.target_if)

    @contextlib.contextmanager
    def configure_eth_if(self) -> Iterator[socket.socket]:
        so = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.htons(self.eth_type))
        so.bind((self.target_if, 0))
        try:
            yield so
        finally:
            so.close()

    def send_eth_packet(self, mac: str) -> None:
        with self.configure_eth_if() as so:
            so.settimeout(10)
            payload = bytearray(1010)
            for i, _ in enumerate(payload):
                payload[i] = i & 0xff
            eth_frame = Ether(dst=mac, src=so.getsockname()[4], type=self.eth_type) / raw(payload)
            try:
                so.send(raw(eth_frame))
            except Exception as e:
                raise e

    def recv_resp_poke(self, i: int) -> None:
        with self.configure_eth_if() as so:
            so.settimeout(10)
            try:
                eth_frame = Ether(so.recv(60))

                if eth_frame.type == self.eth_type and eth_frame.load[0] == 0xfa:
                    if eth_frame.load[1] != i:
                        raise Exception('Missed Poke Packet')
                    eth_frame.dst = eth_frame.src
                    eth_frame.src = so.getsockname()[4]
                    eth_frame.load = bytes.fromhex('fb')    # POKE_RESP code
                    so.send(raw(eth_frame))
            except Exception as e:
                raise e

    def traffic_gen(self, mac: str, pipe_rcv:connection.Connection) -> None:
        with self.configure_eth_if() as so:
            payload = bytes.fromhex('ff')    # DUMMY_TRAFFIC code
            payload += bytes(1485)
            eth_frame = Ether(dst=mac, src=so.getsockname()[4], type=self.eth_type) / raw(payload)
            try:
                while pipe_rcv.poll() is not True:
                    so.send(raw(eth_frame))
            except Exception as e:
                raise e


def ethernet_test(dut: Dut) -> None:
    dut.expect_exact('Press ENTER to see the list of tests')
    dut.write('\n')

    dut.expect_exact('Enter test for running.')
    dut.write('[ethernet]')
    dut.expect_unity_test_output(timeout=980)


def ethernet_int_emac_hal_test(dut: Dut) -> None:
    dut.expect_exact('Press ENTER to see the list of tests')
    dut.write('\n')

    dut.expect_exact('Enter test for running.')
    dut.write('[emac_hal]')
    dut.expect_unity_test_output()


def ethernet_l2_test(dut: Dut) -> None:
    target_if = EthTestIntf(ETH_TYPE)

    dut.expect_exact('Press ENTER to see the list of tests')
    dut.write('\n')
    dut.expect_exact('Enter test for running.')

    with target_if.configure_eth_if() as so:
        so.settimeout(30)
        dut.write('"ethernet broadcast transmit"')
        eth_frame = Ether(so.recv(1024))
        for i in range(0, 1010):
            if eth_frame.load[i] != i & 0xff:
                raise Exception('Packet content mismatch')
    dut.expect_unity_test_output()

    dut.expect_exact("Enter next test, or 'enter' to see menu")
    dut.write('"ethernet recv_pkt"')
    res = dut.expect(
        r'([\s\S]*)'
        r'DUT MAC: ([0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2})'
    )
    time.sleep(1)
    target_if.send_eth_packet('ff:ff:ff:ff:ff:ff')  # broadcast frame
    target_if.send_eth_packet('01:00:00:00:00:00')  # multicast frame
    target_if.send_eth_packet(res.group(2))  # unicast frame
    dut.expect_unity_test_output(extra_before=res.group(1))

    dut.expect_exact("Enter next test, or 'enter' to see menu")
    dut.write('"ethernet start/stop stress test under heavy traffic"')
    res = dut.expect(
        r'([\s\S]*)'
        r'DUT MAC: ([0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2})'
    )
    # Start/stop under heavy Tx traffic
    for tx_i in range(10):
        target_if.recv_resp_poke(tx_i)

    # Start/stop under heavy Rx traffic
    pipe_rcv, pipe_send = Pipe(False)
    tx_proc = Process(target=target_if.traffic_gen, args=(res.group(2), pipe_rcv, ))
    tx_proc.start()
    try:
        for rx_i in range(10):
            target_if.recv_resp_poke(rx_i)
    finally:
        pipe_send.send(0)  # just send some dummy data
        tx_proc.join(5)
        if tx_proc.exitcode is None:
            tx_proc.terminate()
    dut.expect_unity_test_output(extra_before=res.group(1))


@pytest.mark.esp32
@pytest.mark.ethernet
@pytest.mark.parametrize('config', [
    'default_ip101',
    'release_ip101',
    'single_core_ip101'
], indirect=True)
@pytest.mark.flaky(reruns=3, reruns_delay=5)
def test_esp_ethernet(dut: Dut) -> None:
    ethernet_test(dut)


@pytest.mark.esp32
@pytest.mark.ethernet
@pytest.mark.parametrize('config', [
    'default_ip101',
], indirect=True)
@pytest.mark.flaky(reruns=3, reruns_delay=5)
def test_esp_emac_hal(dut: Dut) -> None:
    ethernet_int_emac_hal_test(dut)


@pytest.mark.esp32
@pytest.mark.ip101
@pytest.mark.parametrize('config', [
    'default_ip101',
], indirect=True)
@pytest.mark.flaky(reruns=3, reruns_delay=5)
def test_esp_eth_ip101(dut: Dut) -> None:
    ethernet_l2_test(dut)


@pytest.mark.esp32
@pytest.mark.lan8720
@pytest.mark.parametrize('config', [
    'default_lan8720',
], indirect=True)
@pytest.mark.flaky(reruns=3, reruns_delay=5)
def test_esp_eth_lan8720(dut: Dut) -> None:
    ethernet_l2_test(dut)
