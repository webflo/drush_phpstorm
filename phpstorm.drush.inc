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
  $kernel = new \Drupal\Core\DrupalKernel('prod', drupal_classloader(), FALSE);
  $kernel->boot();
  $request = \Symfony\Component\HttpFoundation\Request::createFromGlobals();
  \Drupal::getContainer()->set('request', $request);

  $dump = new Symfony\Component\DependencyInjection\Dumper\XmlDumper($kernel->getContainer());
  file_put_contents(DRUPAL_ROOT . '/.container.xml', $dump->dump());
}
