import binascii
import sys

# Constants.
BOOT2_START = 4096 # Number of bytes before second stage boot section.
BOOT2_LENGTH = 252 # Length of second stage boot section in bytes.
CRC_LENGTH = 4 # Length of CRC in bytes.

# Taken from https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2_common/boot_stage2/pad_checksum
def bitrev(x, width):
    return int("{:0{w}b}".format(x, w=width)[::-1], 2)

read_bytes = None

# Open the input file in read bytes format.
with open(sys.argv[1], "rb") as f:
    read_bytes = f.read()

# Isolate the second stage boot section from the ELF file.
boot2_bytes = read_bytes[BOOT2_START:BOOT2_START + BOOT2_LENGTH]

# Convert immutable bytes to mutable byte array so we can write the CRC to the file.
new_bytes = bytearray(read_bytes)

# Calculate the CRC over the second stage boot section. Taken from https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2_common/boot_stage2/pad_checksum
pico_sdk_crc = bitrev((binascii.crc32(bytes(bitrev(b, 8) for b in boot2_bytes), 0xffffffff ^ 0xffffffff) ^ 0xffffffff) & 0xffffffff, 32).to_bytes(4, 'little')

# Insert the calculated CRC into the ELF file.
for i in range(BOOT2_START + BOOT2_LENGTH, BOOT2_START + BOOT2_LENGTH + CRC_LENGTH):
    new_bytes[i] = pico_sdk_crc[i - (BOOT2_START + BOOT2_LENGTH)]

# Print user feedback.
print("Adding CRC 0x" + pico_sdk_crc.hex() + " to file " + sys.argv[1])

# Overwrite the existing ELF file with the new one.
with open(sys.argv[1], "wb") as f:
    f.write(new_bytes)
