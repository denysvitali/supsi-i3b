/******************************************************************************
* Filter class
******************************************************************************/
template <typename SampleType>
class MyFilter {
public:
	MyFilter(int lowFrequency, int highFrequency, double sampleRate)
		: filterLowPass(dsp::IIR::Coefficients<SampleType>::makeLowPass(sampleRate, highFrequency))
		, filterHighPass(dsp::IIR::Coefficients<SampleType>::makeHighPass(sampleRate, lowFrequency))
	{
		assert(lowFrequency < highFrequency);
		assert((int) sampleRate >  (highFrequency / 2)); // Nyquist
		dsp::ProcessSpec spec{ sampleRate, 8192, 1 };
		filterLowPass.prepare(spec);
		filterHighPass.prepare(spec);
	}
	~MyFilter() { /* Intentionally empty */ }
	void process(SampleType *block, size_t blockSize) {
		SampleType *cc[1] = { block };
		SampleType* const* channels = cc;
		dsp::AudioBlock<SampleType> audioblock(channels, 1, blockSize);
		dsp::ProcessContextReplacing<SampleType> context(audioblock);
		filterLowPass.process(context);
		filterHighPass.process(context);
	}
private:
	dsp::IIR::Filter<SampleType> filterLowPass;
	dsp::IIR::Filter<SampleType> filterHighPass;
};

