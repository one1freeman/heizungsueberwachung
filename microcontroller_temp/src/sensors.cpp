int cycleCounter = 0;
float getSensorData(int id) {
    if (cycleCounter == 10)
    {
        cycleCounter = 0;
    }
    
    float value = 60.261 + id + cycleCounter*0.5;
    cycleCounter++;
    return value;
}