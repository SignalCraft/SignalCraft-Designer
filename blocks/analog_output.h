struct analog_output_options {
	int channel;
};

void analog_output (struct analog_output_options *options, int16_t *in0) {
	write_dac(options->channel, *in0);
}