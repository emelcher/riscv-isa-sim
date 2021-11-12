// vnclip: vd[i] = clip(round(vs2[i] + rnd) >> simm)
VRM xrm = p->VU.get_vround_mode();
int64_t int_max = INT64_MAX >> (64 - p->VU.vsew);
int64_t int_min = INT64_MIN >> (64 - p->VU.vsew);
VI_VVXI_LOOP_NARROW
({
  int128_t result = vs2;
  unsigned shift = zimm5 & ((sew * 2) - 1);

  // rounding
  INT_ROUNDING(result, xrm, shift);

  result = result >> shift;

  // saturation
  if (result < int_min) {
    result = int_min;
    P_SET_OV(1);
  } else if (result > int_max) {
    result = int_max;
    P_SET_OV(1);
  }

  vd = result;
}, false)
