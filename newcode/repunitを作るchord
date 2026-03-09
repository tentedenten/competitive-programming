
auto repunit = [&](int l) {
    mint res = 0, x = 1, ten = 10;
    while (l) {
      if (l%2) res = res*ten + x;
      x = x*ten + x;
      ten *= ten;
      l /= 2;
    }
    return res;
  };
