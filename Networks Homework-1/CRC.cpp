/*
-----------------------------------------
HOW TO COMPILE AND RUN:

1. Save this file as: crc.cpp
2. Compile:
   g++ crc.cpp -o crc
3. Run:
   ./crc
-----------------------------------------
This program:
1. Generates a 10-bit data block D.
2. Uses CRC pattern P = 110101.
3. Computes CRC bits (length = divisor.length() - 1).
4. Forms transmitted frame T.
5. Introduces a transmission error.
6. Checks whether received frame is accepted or discarded.
-----------------------------------------
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/* XOR Operation */
string xorOperation(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++)
        result += (a[i] == b[i]) ? '0' : '1';
    return result;
}

/* CRC Computation */
string computeCRC(string data, string divisor) {
    int m = divisor.length();
    string temp = data.substr(0, m);

    for (int i = m; i < data.length(); i++) {
        if (temp[0] == '1')
            temp = xorOperation(divisor, temp) + data[i];
        else
            temp = xorOperation(string(m, '0'), temp) + data[i];
    }

    if (temp[0] == '1')
        temp = xorOperation(divisor, temp);
    else
        temp = xorOperation(string(m, '0'), temp);

    // Ensure remainder length is exactly m-1
    return temp.substr(0, m - 1);
}

int main() {

    srand(time(0));

    // Step (a): Generate random 10-bit message
    string data = "";
    for (int i = 0; i < 10; i++)
        data += (rand() % 2) ? '1' : '0';

    cout << "Generated 10-bit message D: " << data << endl;

    // Step (b): Use P = 110101
    string divisor = "110101";
    cout << "Using CRC pattern P: " << divisor << endl;

    // Append r zeros
    int r = divisor.length() - 1;
    string appendedData = data + string(r, '0');

    // Compute CRC
    string remainder = computeCRC(appendedData, divisor);

    // Create transmitted frame T
    string transmittedFrame = data + remainder;

    cout << "CRC bits (" << r << " bits): " << remainder << endl;
    cout << "Transmitted Frame T (15 bits): " << transmittedFrame << endl;

    // Step (c): Introduce transmission error
    string receivedFrame = transmittedFrame;

    int errorPosition = rand() % receivedFrame.length();
    receivedFrame[errorPosition] =
        (receivedFrame[errorPosition] == '1') ? '0' : '1';

    cout << "Error introduced at bit position: "
         << errorPosition + 1 << endl;
    cout << "Received Frame: " << receivedFrame << endl;

    // Step (d): Apply CRC to received frame
    string checkRemainder = computeCRC(receivedFrame, divisor);

    bool errorDetected =
        (checkRemainder.find('1') != string::npos);

    if (errorDetected)
        cout << "Result: Frame Discarded (Error Detected)" << endl;
    else
        cout << "Result: Frame Accepted (No Error)" << endl;

    return 0;
}