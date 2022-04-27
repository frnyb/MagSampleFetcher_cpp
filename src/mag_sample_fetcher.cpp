#include "mag_sample_fetcher.h"

MagSampleFetcher::MagSampleFetcher(unsigned int bram_uio_number, unsigned int bram_size) 
        : bram(bram_uio_number, bram_size) {
    XMagsamplefetcher_Initialize(&xmsf, "MagSampleFetcher");
}

MagSampleFetcher::~MagSampleFetcher() {
    XMagsamplefetcher_Release(&xmsf);
}

bool MagSampleFetcher::Start(unsigned int n_periods) {

    if(!XMagsamplefetcher_IsIdle(&xmsf)) {

        return false;

    }

    XMagsamplefetcher_Set_n_periods(&xmsf, n_periods);

    return Start();

}

bool MagSampleFetcher::Start() {

    if(!XMagsamplefetcher_IsIdle(&xmsf)) {

        return false;

    }

    XMagsamplefetcher_Start(&xmsf);

    return true;

}

 bool MagSampleFetcher::GetSamples(std::vector<MagSample> *samples) {

    if(!XMagsamplefetcher_IsIdle(&xmsf)) {

        return false;

    }

	int n_samples = XMagsamplefetcher_Get_n_samples_out(&xmsf);

    std::cout << std::to_string(n_samples) << std::endl;

    for (int i = 0; i < n_samples; i++) {

        MagSample mag_sample(&bram, i*12);
        samples->push_back(mag_sample);

    }

    return true;
}

bool MagSampleFetcher::IsRunning() {

    if(!XMagsamplefetcher_IsIdle(&xmsf)) {

        return true;

    } else {

        return false;

    }
}