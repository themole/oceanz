#ifndef PERLIN_HH_SEEN
#define PERLIN_HH_SEEN

class Perlin {

    public:
        Perlin() {
            _seed        = 0;
            _octaves     = 8;
            _amplitude   = 1.f;
            _freq_0      = 1.f;
            _persistence = 0.5f;
        }

        ~Perlin() {}

        // getter
        long  seed()        const { return _seed;        }
        int   octaves()     const { return _octaves;     }
        float amplitude()   const { return _amplitude;   }
        float freq_0()      const { return _freq_0;      }
        float persistence() const { return _persistence; }

        // setter
        void seed( long s ) { _seed = s; }

        void octaves( int o ) {
            if( o > 0 )
                _octaves = o;
        }

        void amplitude( float amp ) {
            if( amp > 0.f )
                _amplitude = amp;
        }

        void freq_0( float f ) {
            if( f > 0.f )
                _freq_0 = f;
        }

        void persistence( float p ) {
            if( p > 0.f && p < 1.f )
                _persistence = p;
        }
        
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

        // one dimensional
        // fractional sum of succesive perlin noises
        // with different frequencies
        float Noise( float x, float y ) const;

        // one dimensional
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
