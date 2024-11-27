#ifndef CHUNK_H
#define CHUNK_H


class Chunk {
    public :
        const static int CHUNK_SIZE = 16;
        const static int CHUNK_HEIGHT = 12;
        const static int CHUNK_SCALE = 1;
        const static int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
        const static int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
};


#endif // CHUNK_H