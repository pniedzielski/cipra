# Release Changes

## Version 1.2

  * Add support for variadic templates in MSVC11.
  * CIPRA_USE_VARIADIC_TEMPLATES no longer has any effect; variadics are on by
    default (even in MSVC11, which doesn't have language variadic templates).
  * Fix to new_ok() on move only types.
  * Add a CMake Config.cmake file so CMake projects can find cipra if it is
    installed.

### Bugfix 1.2.1

  * Fixed bug in CMake Config.cmake file that prevents cipra from being found
    when a specific version is requested (even if the version is present).

## Version 1.1

  * Switched to CMake build system.
  * Created pkg-config file.
  * Added tutorial to documentation.
  * Add traits class templates to allow users to specialize how to
    print and check for equality for their types.

## Version 1.0

  * Initial version.
  * Supports Test::More's interface.
  * Header-only library.
  * Thread-safe.
  * Example test files.