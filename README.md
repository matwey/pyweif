[![Python package](https://github.com/matwey/pyweif/actions/workflows/python-package.yml/badge.svg)](https://github.com/matwey/pyweif/actions/workflows/python-package.yml)

# pyweif

**pyweif** is a Python library for calculating weight functions for optical turbulence in the atmosphere.
It is a wrapper around the [libweif](https://libweif.readthedocs.io) C++ library built with [nanobind](https://nanobind.readthedocs.io).

## Documentation

Complete documentation is available at **[https://pyweif.readthedocs.io](https://pyweif.readthedocs.io)**.

The documentation includes:
- [Tutorials](https://pyweif.readthedocs.io/en/latest/tutorials.html) – Jupyter notebook examples of common use cases.
- [How‑to guides](https://pyweif.readthedocs.io/en/latest/howto.html) – installation and building instructions.
- [API reference](https://pyweif.readthedocs.io/en/latest/autoapi/index.html) – detailed class and function descriptions.
- [Internals](https://pyweif.readthedocs.io/en/latest/internals.html) – design decisions, versioning policy, and unit conventions.

## Quick Installation

The easiest way to install pyweif is via pip:

```bash
pip install pyweif
```

Pre-built wheels are available for many Python versions and Linux platforms. The wheels already include the required C++ dependencies, so you do not need to install anything separately.

If you need to build pyweif from source, you can install directly from the repository. For detailed installation instructions, see the [Installation guide](https://pyweif.readthedocs.io/en/latest/howto.html#installation).

## Minimal Example

```python
import numpy as np

import pyweif.sf as sf
import pyweif.af as af
from pyweif import WeightFunction

# Create a monochromatic spectral filter
spectral_filter = sf.Mono()

# Create a circular aperture filter
aperture_filter = af.Circular()

# Construct the weight function for wavelength 500 nm,
# aperture diameter 10 mm, interpolation grid size 1024
wf = WeightFunction(spectral_filter, 500.0, aperture_filter, 10.0, 1024)

# Evaluate the weight at altitudes 0.5, 1, 2, and 4 km
value = wf(np.array([0.5, 1.0, 2.0, 4.0]))
```

More examples are available in the [Tutorials](https://pyweif.readthedocs.io/en/latest/tutorials.html) and in the `docs/notebooks/` directory.

## Contributing

You are welcome to report issues on the [GitHub Issues page](https://github.com/matwey/pyweif/issues).
Pull requests are also accepted on GitHub.
Please see the [Contributing guide](https://pyweif.readthedocs.io/en/latest/howto.html#contributing) for details.

## License

pyweif is licensed under the **GNU General Public License v3.0 or later**.
See the [LICENSE](LICENSE) file for details.
