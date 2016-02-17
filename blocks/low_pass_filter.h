struct low_pass_filter_options {
  uint16_t factor;
};

int32_t low_pass_filter_acc = 0;

void low_pass_filter(struct low_pass_filter_options *options, int *in, int *out) {
	low_pass_filter_acc *= options->factor;
	low_pass_filter_acc += ((int32_t)(*in) * (~(options->factor) + 1));
	low_pass_filter_acc = low_pass_filter_acc >> 16;
	*out = (int16_t)low_pass_filter_acc;
}

