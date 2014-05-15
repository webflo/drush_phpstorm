# Drush PhpStorm Metadata Generator

PhpStrom provides support for type hint and completion of static factories.

Related links

- [PhpStorm Advanced Metadata](http://confluence.jetbrains.com/display/PhpStorm/PhpStorm+Advanced+Metadata)
- [WI-6027 Generic support for factory design pattern in PHP chaining](http://youtrack.jetbrains.com/issue/WI-6027)

## Usage

Clone this project and run the following drush command in your Drupal 8 installation.

```
drush phpstorm-metadata
```

## Known issues

- [WI-22295 static factory method autocomplete doesn't work with keys which contains dots](http://youtrack.jetbrains.com/issue/WI-22295)
