#!/usr/bin/env python

from distutils.core import setup

setup(name='python-kredsrpc',
      version='0.1',
      description='Enhanced version of python-jsonrpc for use with Kreds',
      long_description=open('README').read(),
      author='Jeff Garzik',
      author_email='<jgarzik@exmulti.com>',
      maintainer='Jeff Garzik',
      maintainer_email='<jgarzik@exmulti.com>',
      url='http://www.github.com/jgarzik/python-kredsrpc',
      packages=['kredsrpc'],
      classifiers=['License :: OSI Approved :: GNU Library or Lesser General Public License (LGPL)', 'Operating System :: OS Independent'])
