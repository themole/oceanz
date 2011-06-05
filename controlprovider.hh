#ifndef CONTROLPROVIDER_HH
#define CONTROLPROVIDER_HH

#include <citycontrol.hh>

class ControlProvider {
public:
    static CityControl const & cityControl();
    static void registerCityControl( CityControl & cc );

private:
    static CityControl _cc;
};

#endif // CONTROLPROVIDER_HH
