#include <stdbool.h>

class DHT11 {
    public:
        DHT11(int pin);
        void init(void);
        bool read(int *humidity, int *temperature);
        
    private:
        int dht11_pin;

};


