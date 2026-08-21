import asyncio
import keyboard
from bleak import BleakScanner, BleakClient
async def main():
    devices = await BleakScanner.discover()
    for d in devices:
        print(d.name, d.address)
        if d.name == "SpidBot":
            async with BleakClient(d.address) as client:
                print("Connected:", client.is_connected)
                while True:
                    if keyboard.is_pressed('o'):
                        await client.write_gatt_char("67c9803f-9d13-4131-9465-2d36f29c603d", "o".encode())
                    elif keyboard.is_pressed('f'):
                        await client.write_gatt_char("67c9803f-9d13-4131-9465-2d36f29c603d", "f".encode())
                    elif keyboard.is_pressed('q'):
                        break
                    await asyncio.sleep(0.1)
asyncio.run(main())