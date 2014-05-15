<?php

/**
 * @file
 * Generate PhpStorm metadata file.
 */

/**
 * Implements of hook_drush_command().
 */
function phpstorm_drush_command() {
  $items = array();

  $items['phpstorm-metadata'] = array(
    'description' => 'Generate PhpStorm Metadata file',
  );

  return $items;
}

/**
 * Generate PhpStorm Metadata file.
 *
 * @see http://confluence.jetbrains.com/display/PhpStorm/PhpStorm+Advanced+Metadata
 */
function drush_phpstorm_metadata() {
  $container = \Drupal::getContainer();

  $reflectedClass = new ReflectionClass($container);
  $property = $reflectedClass->getProperty('services');
  $property->setAccessible(true);
  $services = $property->getValue($container);

  $map = array();

  foreach ($services as $id => $class) {
    $map[$id] = get_class($class);
  }

$file = '<?php

namespace PHPSTORM_META {

  /** @noinspection PhpUnusedLocalVariableInspection */
  /** @noinspection PhpIllegalArrayKeyTypeInspection */
  $STATIC_METHOD_TYPES = [
';
$file .= "\n";
$file .= "    \Drupal::service('') => [\n";

foreach ($map as $id => $class) {
$file .= "      '$id' instanceof \\$class,\n";
}
$file .= "    ], \n";

$file .= '
  ];
}
';

  file_put_contents(DRUPAL_ROOT . '/.phpstorm.meta.php', $file);
}
