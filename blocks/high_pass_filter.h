struct high_pass_filter_options {
  uint16_t factor;
};

int32_t high_pass_filter_acc = 0;

void high_pass_filter(struct high_pass_filter_options *options, int *in, int *out) {
	high_pass_filter_acc *= options->factor;
	high_pass_filter_acc += ((int32_t)(*in) * (~(options->factor) + 1));
	high_pass_filter_acc = high_pass_filter_acc >> 16;
	*out = *in - ((int16_t)high_pass_filter_acc);
}

