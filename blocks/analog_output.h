struct analog_output_options_int {
	int channel;
};

struct analog_output_options_afp {
	int channel;
};

struct analog_output_options_float {
	int channel;
};

void analog_output_int (struct analog_output_options_int *options, int *in0) {
	write_dac(options->channel, (*in0 >> 16));
}

void analog_output_afp (struct analog_output_options_afp *options, int *in0) {
	write_dac(options->channel, (*in0 >> 16));
}

void analog_output_float (struct analog_output_options_int *options, float *in0) {
	write_dac(options->channel, (int16_t)(*in0));
}