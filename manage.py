#!/usr/bin/env python2
import os
import sys

import django
if django.VERSION < (1, 7):
    raise RuntimeError('requires django v1.7 or greater')

if __name__ == "__main__":
    os.environ.setdefault("DJANGO_SETTINGS_MODULE", "sneezy.settings")

    from django.core.management import execute_from_command_line

    execute_from_command_line(sys.argv)
