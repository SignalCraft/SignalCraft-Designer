struct analog_input_options {
	int channel;
};

void analog_input (struct analog_input_options *options, int *out0) {
	*out0 = (int)read_adc(options->channel) << 16;
}