#include <mbed.h>
#include <features/netsocket/cellular/onboard_modem_api.h>
#include "UbloxATCellularInterfaceN2xx.h"

#if MODEM_ON_BOARD != 1
#error "MODEM ON BOARD NOT ACTIVATED!!!"
#endif

//AT modem initialized on pins MDMTXD, MDMRXD
//at baud MBED_CONF_UBLOX_CELL_N2XX_BAUD_RATE (115200?)
//and debug = false
//see constructor / header
UbloxATCellularInterfaceN2xx myModem;

//see https://platformio.org/lib/show/5284/ublox-at-cellular-interface-n2xx
//see https://platformio.org/lib/show/5286/ublox-cellular-base-n2xx


// The credentials of the SIM in the board.  If PIN checking is enabled
// for your SIM card you must set this to the required PIN.
#define PIN "0000"

// Network credentials.  You should set this according to your
// network/SIM card.  For C030 non-N2xx boards, leave the parameters as NULL
// otherwise, if you do not know the APN for your network, you may
// either try the fairly common "internet" for the APN (and leave the
// username and password NULL), or you may leave all three as NULL and then
// a lookup will be attempted for a small number of known networks
// (see APN_db.h in mbed-os/features/netsocket/cellular/utils).
#define APN         NULL
#define USERNAME    NULL
#define PASSWORD    NULL

int main() {

    //call into low-level init
    //probably not needed
    onboard_modem_init();

    //use myModem somehow

    myModem.set_credentials(APN, USERNAME, PASSWORD);
    for (int x = 0; myModem.connect(PIN) != 0; x++) {
        if (x > 0) {
            printf("Retrying (have you checked that an antenna is plugged in and your APN is correct?)...\n");
            wait_ms(1000);
        }
    }
    printf("We are connected!! :)\n");

    return 0;
}