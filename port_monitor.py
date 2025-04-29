import socket
import struct
import datetime
import csv
import subprocess
import sys

firstData = False

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(('0.0.0.0', 5500))
udpPath = "/home/ali/Github/aras_ir_tracker/udp_aggregator/udp_aggregator.py"
timestamp = datetime.datetime.now().strftime('%Y-%m-%d_%H:%M')
with open(f"Dataset_{timestamp}.csv", "a", newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Enc1", "Enc2", "Enc3", "Enc_Timestamp", "IR_Timestamp"])
    file.flush()
    while True:
        data, addr = sock.recvfrom(1024)
        if not firstData:
            firstData = True
            p = subprocess.Popen(["python3", udpPath], stdout=sys.stdout, stderr=sys.stderr)
        try:
            str1, str2, str3, str4, str5 = struct.unpack('3i2Q', data)
            sender_ip, sender_port = addr
            writer.writerow([str1, str2, str3, str4, str5])
            file.flush()
            print(f"Received message: {str1, str2, str3, str4, str5} from {addr}")
        except struct.error:
            print(f"Error unpacking data from {addr}")
            continue
