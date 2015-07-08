from unittest import TestCase

from sneezy.test import SneezyInstance

class NewInstanceTest(TestCase):
    def test_new_instance_creation(self):
        instance = SneezyInstance()
