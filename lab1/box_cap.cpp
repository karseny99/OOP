const unsigned int box_size = 16;

unsigned int box_capacity(unsigned int length, unsigned int width, unsigned int height) {
    return (length * 12 / box_size) * (width * 12 / box_size) * (height * 12 / box_size);
}