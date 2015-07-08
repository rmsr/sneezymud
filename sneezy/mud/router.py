# Routes all models regarding the given app label to the given db
#
# We return None to explicitly mark where the router has no opinion.

class BaseRouter(object):
    """ subclasses must define self.app_label and self.database """

    def db_for_read(self, model, **hints):
        if model._meta.app_label == self.app_label:
            return self.database
        return None

    def db_for_write(self, model, **hints):
        return self.db_for_read(model, **hints)

    def allow_relation(self, obj1, obj2, **hints):
        # our models only relate to themselves
        if obj1._meta.app_label == self.app_label:
            if obj2._meta.app_label == self.app_label:
                return True
            return False
        elif obj2._meta.app_label == self.app_label:
            return False
        return None

    def allow_migrate(self, db, app_label, model_name=None, **hints):
        # our database only permits our models in it
        if db == self.database:
            return app_label == self.app_label
        if app_label == self.app_label:
            return False
        return None

    # v1.7 compat
    def _allow_migrate_old(self, db, model):
        # our database only permits our models in it
        if db == self.database:
            return model._meta.app_label == self.app_label
        if model._meta.app_label == self.app_label:
            return False
        return None

class MudRouter(BaseRouter):
    app_label = 'mud'
    database = 'mud'

import django
if django.VERSION < (1, 8):
    BaseRouter.allow_migrate = BaseRouter._allow_migrate_old
