#include "mag_sample_fetcher.h"

MagSampleFetcher::MagSampleFetcher(unsigned int bram_uio_number, unsigned int bram_size) 
        : bram(bram_uio_number, bram_size) {
    XMagsamplefetcher_Initialize(&xmsf, "MagSampleFetcher");
}

MagSampleFetcher::~MagSampleFetcher() {
    XMagsamplefetcher_Release(&xmsf);
}

std::vector<MagSample> MagSampleFetcher::GetSamples() {
    while(!XMagsamplefetcher_IsIdle(&xmsf));

    XMagsamplefetcher_Start(&xmsf);

	while(!XMagsamplefetcher_IsIdle(&xmsf));

	int n_samples = XMagsamplefetcher_Get_n_samples_out(&xmsf);

    std::vector<MagSample> samples;

    for (int i = 0; i < n_samples; i++) {
        MagSample mag_sample(&bram, i*12);
        samples.push_back(mag_sample);
    }

    return samples;
}

std::vector<MagSample> MagSampleFetcher::GetSamples(unsigned int n_periods) {
    while(!XMagsamplefetcher_IsIdle(&xmsf));

    XMagsamplefetcher_Set_n_periods(&xmsf, n_periods);

    return GetSamples();
}

