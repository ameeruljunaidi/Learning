"""
This type stub file was generated by pyright.
"""

import contextlib

"""Utility functions used by sql.py.
"""
def process_select_result(result): # -> list[dict[Unknown, Unknown]]:
    """Converts a SQLAlchemy result to a ``list`` of ``dict`` objects, each of which represents a
    row in the result set.

    :param result: A SQLAlchemy result
    :type result: :class:`sqlalchemy.engine.Result`
    """
    ...

@contextlib.contextmanager
def raise_errors_for_warnings(): # -> Generator[None, None, None]:
    """Catches warnings and raises errors instead.
    """
    ...

def postgres_lastval(connection): # -> None:
    """
    :returns: The ID of the last inserted row, if defined in this session, or None
    """
    ...
