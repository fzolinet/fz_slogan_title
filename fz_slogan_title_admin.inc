<?php

/**
 * implements hook_help()
 */
function fz_slogan_title_help($path, $arg) {
  $output = NULL;
  switch ($path) {
    case 'admin/help#fz_slogan_title':
      $output = '<h3>' .t('About'). '</h3>';
      $path   = drupal_get_path('module', 'fz_slogan_title') . '/fz_slogan_title.info';
      $info   = drupal_parse_info_file($path);
      $output .= 'Author: <a href="http://www.fzolee.hu">Zoltan Fabian</a><br/>';
      $output .= t('version').': '.$info['version'].'<br/>';
      $output .= t('compiled').': '.date('Y.m.d',$info['datestamp']);
      $output .= '<p>' . t('Drupal\'s default page change random, cyclic or random with weight') . '</p>';
      $output .= '<p>' . t('FZ Slogan Title provides random, cyclic os random with weight contorol over the &lt;title> and slogan  (&lt;h1> )element on the page');
      $output .= '<p>' . l(t('More Help...'), 'admin/help/config/search/fz_slogan_title') . '</p>';
      break;
  }
  return $output;
}

/**
 * Implements hook_permission().
 */
function fz_slogan_title_permission() {
  return array(
      'administer fz_slogan_title' => array(
          'title' => t('Administer fz_slogan_title'),
          'restrict access' => TRUE,
          'description' => t('Administer FZ Slogan Title.'),
      ),
  );
}

/**
 * Implements hook_menu().
 */
function fz_slogan_title_menu() {
  $items = array();

  $items['admin/config/fz/fz_slogan_title'] = array(
      'title'            => 'FZ Slogan and Title',
      'description'      => 'Adjust FZ Slogan Title settings.',
      'page callback'    => 'drupal_get_form',
      'page arguments'   => array('fz_slogan_title_settings'),
      'access arguments' => array('administer site configuration'),
      'type' => MENU_NORMAL_ITEM,
  );
  return $items;
}

/**
 *  Admin interface for FZ Slogan and Title
 */
function fz_slogan_title_settings(){
  $form = array();

 /* $all = variable_get('fz_slogan_title_all',True);
  $form['fz_slogan_title_all'] = array(
      '#type'  => 'checkbox',
      '#title' => t('Slogan and Title the same in every page'),
      '#default_value' => $all,
      '#description' => t("The titles and slogans are the same all the time"),
  );
  */
  $form['fz_slogan_title_scycle'] = array(
      '#type'  => 'radios',
      '#title' => t('Choose between random, cyclic or random with weight using in sloganes'),
      '#default_value' => variable_get('fz_slogan_title_scycle', 'random'),
      '#options' => array('random' => t('Random'), 'cycling' => t('Cycling'), 'weight' => t('Random with Weight')),
      '#description' => t("Every row new sentence. If you use weight the terminator sign is | sign. First is the sentences, after the weight"),
  );
  
  $slogans= variable_get("fz_slogan_title_slist");

  $form['fz_slogan_title_slist'] = array(
      '#type'          => 'textarea',
      '#title'         => t('Sentences for slogans'),
      '#default_value' => $slogans,
      '#description'   => t("Every row a new sentence")
  );
  
  $sidx = variable_get('fz_slogan_title_sindex',0);
  $texts = preg_split("/\n/",$slogans );

  $form['fz_slogan_title_sactual'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Actual sentence'),
      '#default_value' => $texts[$sidx],
      '#description'   => t("Actual slogan"),
      '#attributes'    => array('readonly' => 'readonly'),
  );
  
  $form["fz_slogan_title"] =array(
     '#type'           => "checkbox",
      '#default_value' => variable_get("fz_slogan_title", true),
      '#title'         => t('Title of html header'),
  );
  
  $form["fz_slogan_slogan"] =array(
      '#type'          => "checkbox",
      '#default_value' =>  variable_get("fz_slogan_slogan", true),
      '#title'         => t('Slogan of site'),
  );
  //Slogan actual CSS settings
 /* $form['fz_slogan_name_css'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Actual CSS settings'),
      '#default_value' => variable_get("fz_slogan_name_css",""),
      '#description'   => t("Actual CSS settings"),
      //'#attributes'    => array('readonly' => ''),
  ); */
  $form = system_settings_form($form);
  return $form;
}
