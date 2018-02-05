from distutils.core import setup
setup(name='btcspendfrom',
      version='1.0',
      description='Command-line utility for kreds "coin control"',
      author='Gavin Andresen',
      author_email='gavin@kredsfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
