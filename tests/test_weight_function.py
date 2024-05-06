import pytest
import pyweif
from pyweif import WeightFunction, WeightFunction2d
import unittest
import numpy as np


class TestWeightFunction:
	@pytest.mark.benchmark(group="pyweif.WeightFunction", min_rounds=10, disable_gc=True, warmup=False)
	@pytest.mark.parametrize("size", [128, 1024, 4096])
	def test_mono_point(self, size, benchmark):
		sf = pyweif.sf.Mono()
		af = pyweif.af.Point()

		@benchmark
		def construct():
			wf = WeightFunction(sf, 550, af, 1, size)
			assert wf(0) == 0

	@pytest.mark.benchmark(group="pyweif.WeightFunction", min_rounds=10, disable_gc=True, warmup=False)
	@pytest.mark.parametrize("size", [128, 1024])
	def test_mono_point_python(self, size, benchmark):
		class Mono:
			def __call__(self, x):
				return np.sin(np.pi * x)**2

			def regular(self, x):
				return np.sinc(x)**2

		class Point:
			def __call__(self, x):
				return 1.0

		@benchmark
		def construct():
			wf = WeightFunction(Mono(), 550, Point(), 1, size)
			assert wf(0) == 0

class TestWeightFunction2d:
	@pytest.mark.benchmark(group="pyweif.WeightFunction2d", min_rounds=10, disable_gc=True, warmup=False)
	@pytest.mark.parametrize("size", [128, 1024, 4096])
	def test_mono_point(self, size, benchmark):
		sf = pyweif.sf.Mono()
		af = pyweif.af.Point()

		@benchmark
		def construct():
			wf = WeightFunction2d(sf, 550, af, 1, size)
			assert wf(0) == 0

if __name__ == '__main__':
	unittest.main()
