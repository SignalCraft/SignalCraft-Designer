struct high_pass_filter_options {
  uint16_t factor;
};

int32_t high_pass_filter_acc = 0;

void high_pass_filter(struct high_pass_filter_options *options, int16_t *in, int16_t *out) {
	high_pass_filter_acc *= 0xF000;
	high_pass_filter_acc += ((int32_t)(*in) * 0x1000);
	high_pass_filter_acc = high_pass_filter_acc >> 16;
	*out = *in - ((int16_t)high_pass_filter_acc);
}

