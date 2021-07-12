//Initializing code (one-time/reset code)


void initSOH(float newSOH) {
    
    soh = newSOH;
    batteryChargeCapacity = nominalChargeCapacity / 100 * soh;

  }
batteryChargeCapacity = nominalChargeCapacity; 
initSOH(100.0);

//SOH Calculation

#define SMOOTH_CAP          200
 float socCharged = soc - socChargeStartSOC;
          if (socCharged >= 50) {

            unsigned long expectedCharge = batteryChargeCapacity / 100 * soc_charged;
           
            unsigned long realCharge = availableCharge - chargeAvailableAtChargeStart;
            
          
            unsigned long oldCap = batteryChargeCapacity;
            unsigned long newCap = realCharge / socCharged * 100;
            
            batteryChargeCapacity = (oldCap / SMOOTH_CAP) * (SMOOTH_CAP - socCharged)
                    + (newCap / SMOOTH_CAP) * socCharged;
            
            // calculate SOH:
            soh = constrain((float) batteryChargeCapacity / nominalChargeCapacity * 100, 0, 100);

}
