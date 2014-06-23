<?php

/**
 * @file
 * Drush integration for the devel module.
 */

define('NUDATA_COMPONENTS', serialize(array('engage', 'storytelling')));
/**
 * Implements hook_drush_command().
 */
function nudata_drush_command() {
  $items['nudata-enable'] = array(
    'description' => dt('Enables nudata components'),
    'arguments' => array(
      'components' => dt('Lists of components eg: drush nudata-enable engage storytelling'),
    ),
    'aliases' => array('nuen'),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function nudata_drush_help($command) {
  switch ($command) {
    case 'nudata-enable':
    case 'nuen':
      return dt('Enables nudata components');
      break;
  }
}

// /**
//  * A command callback. This is faster than 3 separate bootstraps.
//  */
// function drush_devel_reinstall() {
//   $projects = func_get_args();

//   $args = array_merge(array('pm-disable'), $projects);
//   call_user_func_array('drush_invoke', $args);

//   $args = array_merge(array('pm-uninstall'), $projects);
//   call_user_func_array('drush_invoke', $args);

//   $args = array_merge(array('pm-enable'), $projects);
//   call_user_func_array('drush_invoke', $args);
// }

/**
 * A command callback.
 */
function drush_nudata_enable($components = NULL) {
  $nudata_components = unserialize(NUDATA_COMPONENTS);
  if (is_null($components)) {
    $components = $nudata_components;
  }

  if (count($components) > 1) {
    foreach ($components as $key => $component) {
      if (!in_array($component, $nudata_components)) {
        drush_log(dt('@component is not a Nudata component', array('@component' => $component)), 'warning');
        unset($components[$key]);
      }
    }
    if (count($components) > 1) {
      $success = module_enable($components);
      if ($success) {
        // drush_log(dt('@components enabled', array('@components' => join(',' $components))), 'success');
      }
      else{
        drush_log(dt('Some components were not enabled, please review their dependencies'), 'error');
      }
    }
  }
  else {
    drush_log(dt('You need to specify at least one component'), 'error');
  }
}
