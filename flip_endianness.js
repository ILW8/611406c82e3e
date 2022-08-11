function reverse_endianness(input_number) {
    let reversed = 0;

    input_number ^= 0; // truncates number to be 32-bit
    for (let i = 0; i < 4; i++) {
        reversed |= (0xFF & (input_number >> 8 * i)) << 8 * (3 - i)
    }

    return reversed;
}