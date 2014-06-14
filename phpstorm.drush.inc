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

  $items['phpstorm-symfony2-metadata'] = array(
    'description' => 'Generate Metadata for PhpStorms Symfony2 Plugin',
  );

  return $items;
}

/**
 * Generate a fully bootstraped kernel.
 *
 * @return \Drupal\Core\DrupalKernel
 */
function _phpstorm_bootstrap_kernel() {
  $kernel = new \Drupal\Core\DrupalKernel('prod', drupal_classloader(), FALSE);
  $kernel->boot();
  $request = \Symfony\Component\HttpFoundation\Request::createFromGlobals();
  \Drupal::getContainer()->set('request', $request);
  return $kernel;
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
  unset($services['service_container']);

  $map = array();

  // Service container
  foreach ($services as $id => $class) {
    $map["\\Drupal::service('')"][$id] = '\\' . get_class($class);
  }

  // Entity Manager - getStorage
  foreach (\Drupal::entityManager()->getDefinitions() as $type => $definition) {
    $class = Drupal::entityManager()->getStorage($type);
    $map["\\Drupal::entityManager()->getStorage('')"][$type] = '\\' . get_class($class);
  }

  $content = _drush_phpstorm_metadata_phpstorm_metadata_template($map);
  file_put_contents(DRUPAL_ROOT . '/.phpstorm.meta.php', $content);
}

function _drush_phpstorm_metadata_phpstorm_metadata_template($data) {
  $file = '<?php

namespace PHPSTORM_META {

  /** @noinspection PhpUnusedLocalVariableInspection */
  /** @noinspection PhpIllegalArrayKeyTypeInspection */
  $STATIC_METHOD_TYPES = [
';

  foreach ($data as $method => $map) {
    $file .= "\n";
    $file .= "    {$method} => [\n";

    foreach ($map as $argument => $class) {
      $file .= "      '{$argument}' instanceof {$class},\n";
    }

    $file .= "    ],";
    $file .= "\n";
  }

  $file .= '
    ];
  }
  ';

  return $file;
}

/**
 * Generate PhpStorm Metadata file.
 *
 * @see http://confluence.jetbrains.com/display/PhpStorm/PhpStorm+Advanced+Metadata
 */
function drush_phpstorm_symfony2_metadata() {
  $kernel = _phpstorm_bootstrap_kernel();
  $dump = new Symfony\Component\DependencyInjection\Dumper\XmlDumper($kernel->getContainer());
  file_put_contents(DRUPAL_ROOT . '/container.xml', $dump->dump());
}
