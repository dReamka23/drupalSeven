<?php
/**
 * Popup’s example form.
 */
function example_popup_form($form, $form_state) {
  $form ['title'] = [
    '#title' => t('Title'),
    '#type' => 'textfield',
  ];
  $form['textarea'] = [
    '#title' => t('Description'),
    '#type' => 'textarea',
  ];
  $form['Email'] = [
    '#title' => t('Email'),
    '#type' => 'textfield',
  ];
  $form['submit'] = [
    '#type' => 'submit',
    '#value' => t('Ok'),
  ];
  return $form;
}

/**
 * Popup’s callback function for form.
 */
function example_popup_callback($js, $nid) {
  global $user;
  ctools_include('node.pages', 'node', '');
  ctools_include('modal');
  ctools_include('ajax');
  $type = 'Reviews';
  $node = (object) [
    'uid' => $user->uid,
    'name' => (isset($user->name) ? $user->name : ''),
    'type' => $type,
    'language' => LANGUAGE_NONE,
    'field_reviews' => [
      'und' => [
        ['target_id' => $nid],
      ],
    ],
  ];

  if (!$js) {
    return drupal_get_form($type . 'example_popup_form', $node);
  }

  $form_state = [
    'ajax' => TRUE,
    'build_info' => [
      'args' => [$node],
    ],
  ];
  $output = ctools_modal_form_wrapper($type . 'example_popup_form', $form_state);
  $output[0]['output'] = '<h2>' . t('Reviews') . '?</h2>'
    . '<p>' . t('Write to us and we will contact you within 2 hours')
    . '</p>' . $output[0]['output'];

  if (!empty($form_state['executed']) || !empty($form_state['ajax_commands'])) {
    $output = [];
    $output[] = ctools_modal_command_dismiss();
    $output[] = ctools_ajax_command_reload();
  }
  print ajax_render($output);
}



