import socket
import math
key = "HACK"
def decryptMessage(cipher):
    msg = ""
    k_indx = 0
    msg_indx = 0
    msg_len = float(len(cipher))
    msg_lst = list(cipher)
    col = len(key)
    row = int(math.ceil(msg_len / col))
    key_lst = sorted(list(key))
    dec_cipher = []
    for _ in range(row):
        dec_cipher += [[None] * col]
    for _ in range(col):
        curr_idx = key.index(key_lst[k_indx])
  
        for j in range(row):
            dec_cipher[j][curr_idx] = msg_lst[msg_indx]
            msg_indx += 1
        k_indx += 1
    try:
        msg = ''.join(sum(dec_cipher, []))
    except TypeError:
        raise TypeError("This program cannot",
                        "handle repeating words.")
    null_count = msg.count('_')
    if null_count > 0:
        return msg[: -null_count]
    return msg
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 1738))
server.listen(5)
conn, addr = server.accept()
print("working")
data = conn.recv(1024)
print(data.decode())
encryptedtext=data.decode()
msg = encryptedtext
print("Decryped Message: {}".
       format(decryptMessage(msg)))