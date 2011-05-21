#ifndef PERLIN_HH_SEEN
#define PERLIN_HH_SEEN

class Perlin {

    public:
        Perlin();
        ~Perlin();

        // getter
        long  seed() const;
        int   octaves() const;
        float amplitude() const; 
        float freq0() const; 
        float persistence() const; 

        // setter
        void setSeed( long s ); 
        void setOctaves( int o ); 
        void setAmplitude( float amp );
        void setFreq0( float f );
        void setPersistence( float p );       

        // one dimensional perlin noise
        // _seed is used as offset for int hashing
        // value is in [ -1.f, 1.f ]
        float noise( float x ) const;

        // two dimensional perlin noise
        // _seed is used as offset for int hashing
        // value is in [ -1.f, 1.f ]
        float noise( float x, float y ) const;

        // three dimensional perlin noise
        // _seed is used as offset for int hashing
        // value is in [ -1.f, 1.f ]
        float noise( float x, float y, float z ) const;
        
        // one dimensional
        // fractional sum of succesive perlin noises
        // with different frequencies
        float Noise( float x ) const;

        // two dimensional
        // fractional sum of succesive perlin noises
        // with different frequencies
        float Noise( float x, float y ) const;

        // three dimensional
        // fractional sum of succesive perlin noises
        // with different frequencies
        float Noise( float x, float y, float z ) const;

        // interpolates between two values using an s-shaped curve
        // x must be in [0.f, 1.f]
        float ease_perlin( float a, float b, float x ) const;

        // returns values in [INT_MIN, INT_MAX]
        int hash_int( int a ) const;

        // hashes two ints to one
        // uses hash_int( int ) -> same value range
        int hash_int( int a, int b ) const;

        // hashes three ints to one
        // see above for range
        int hash_int( int a, int b, int c ) const;

        // return values in [-1.f, 1.f]
        float hash_float( int n ) const;

        // hashes two int to one float
        // third parameter can be used to get different results
        // for same a and b -> bit shifts
        float hash_float( int a, int b, unsigned char bit = 0 ) const;

        // hashes three int to one float
        // parameter 4 as above
        float hash_float( int a, int b, int c, unsigned char bit = 0 ) const;

    private:
        long    _seed;
        int     _octaves;
        float   _amplitude;
        float   _freq_0;
        float   _persistence;
};

#endif // PERLIN_HH_SEEN
