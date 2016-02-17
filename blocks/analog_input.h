struct analog_input_options {
	int channel;
};

void analog_input (struct analog_input_options *options, int16_t *out0) {
	*out0 = read_adc(options->channel);
}