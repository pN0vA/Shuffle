#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <capstone/capstone.h>

using namespace std;

void disassembleShellcode(const unsigned char* shellcode, size_t length) {
    cs_insn* insn;
    csh handle;

    if (cs_open(CS_ARCH_X86, CS_MODE_32, &handle) != CS_ERR_OK) {
        cerr << "Failed to initialize Capstone disassembler" << endl;
        return;
    }

    size_t count = cs_disasm(handle, shellcode, length, 0x1000, 0, &insn);
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            cout << hex << insn[i].address << ": " << insn[i].mnemonic << " " << insn[i].op_str << endl;
        }

        cs_free(insn, count);
    } else {
        cerr << "Failed to disassemble shellcode" << endl;
    }

    cs_close(&handle);
}

void executeShellcode(const unsigned char* shellcode, size_t length) {
    void (*code)() = (void(*)())shellcode;
    code();
}

vector<unsigned char> decodeShellcode(const string& encodedShellcode) {
    vector<unsigned char> decodedShellcode;

    for (int i = 0; i < encodedShellcode.length(); i += 2) {
        string byteString = encodedShellcode.substr(i, 2);
        unsigned char byte = (unsigned char)strtol(byteString.c_str(), NULL, 16);
        decodedShellcode.push_back(byte);
    }

    for (int i = 0; i < decodedShellcode.size(); i++) {
        cout << hex << setw(2) << setfill('0') << (int)decodedShellcode[i] << " ";
    }

    cout << endl;

    return decodedShellcode;
}

int main() {
    string encodedShellcode;
    cout << "\n\nWhat is the shellcode: ";
    cin >> encodedShellcode;

    vector<unsigned char> decodedShellcode = decodeShellcode(encodedShellcode);
    disassembleShellcode(decodedShellcode.data(), decodedShellcode.size());
    executeShellcode(decodedShellcode.data(), decodedShellcode.size());

    return 0;
}
