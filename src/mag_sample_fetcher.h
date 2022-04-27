#pragma once

#include "../include/BRAM-uio-driver/src/bram_uio.h"
#include "../include/PL-Mag-Sensor/ip/MagSampleFetcher/drivers/MagSampleFetcher_v1_0/src/xmagsamplefetcher.h"

#include "stdint.h"

#include <vector>
#include <iostream>
#include <chrono>

#include "mag_sample.h"

class MagSampleFetcher {
public:
    MagSampleFetcher(unsigned int bram_uio_number, unsigned int bram_size);
    ~MagSampleFetcher();

    bool Start(unsigned int n_periods);
    bool Start();

    bool IsRunning();

    bool GetSamples(std::vector<MagSample> *samples);

private:
    BRAM bram;
    XMagsamplefetcher xmsf;

};