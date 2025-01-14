# @page WebSocket: Server

import asyncio;
import websockets;

connected = set();

message = '{"ID":"WsProClient","Networks":[{"ID":1,"Devices":[{"ID":1,"BaseAddr":1,"BL1_1":1,"BL1_2":0,"BL1_3":0,"BL1_4":0,"BL2_1":0,"BL2_2":0,"BL2_3":0,"BL3_1":0,"BL3_2":0,"NUM1_1":0,"NUM1_2":0,"NUM1_3":0,"NUM2_1":0,"NUM2_2":0,"STR":0,"COLOR":0}]}],"Stamp":1735211107}"';

async def ws_handler(websocket):
	UserCount = len(connected);
	UserIP    = websocket.remote_address;
	print(f"{UserIP} [{UserCount}] connected");
	connected.add(websocket);

	try:
		async for message in websocket:
			print(f"{message}");

	except websockets.exceptions.ConnectionClosedOK:
		connected.remove(websocket);
		UserCount = len(connected);
		UserIP    = websocket.remote_address;
		print(f"{UserIP} [{UserCount}] disconnected");

async def main():

	async with websockets.serve(ws_handler, "localhost", 8100):
		await asyncio.Future();

if __name__ == "__main__":
	asyncio.run(main());
