from django.db import models

class FixedCharField(models.Field):
    description = "String of fixed length %(max_length)s"

    def db_type(self, connection):
        return 'char(%s)' % self.max_length
