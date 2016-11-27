<?php

/**
 * Callback management/edit-person/%
 */
function sainet_edit_person($id_user) {
  
  $build = array();
  $build = drupal_get_form('sainet_edit_person_form', $id_user);
  
  return $build;
}

/**
 * Callback sainet_edit_person
 */
function sainet_edit_person_form($form, &$form_state, $id_user) {

  // llamar informacion del usuario seleccionado
  $data_user = _sainet_get_full_data_user($id_user);

  $form['id_user'] = array(
    '#type' => 'value',
    '#value' => $id_user,
  );

  $form['filter'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Form for edit user')
  );

  $form['filter']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('User names'),
    '#required' => TRUE,
    '#default_value' => $data_user['name'],
  );

  $form['filter']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#description' => t('Surname of the user'),
    '#required' => TRUE,
    '#default_value' => $data_user['last_name'],
  );

  $options_genre = array(
    t('Woman') => t('Woman'),
    t('Man') => t('Man'),
  );
  $form['filter']['genre'] = array(
    '#title' => t('Genre'),
    '#description' => t('Sex of the user'),
    '#type' => 'select',
    '#options' => $options_genre,
    '#default_value' => $data_user['genre'],
    '#required' => TRUE,
  );

  $birthdate_format = array();
  $birthdate = explode('/', $data_user['birthdate']);

  $birthdate_format = array(
    'month' => $birthdate[1],
    'day' => $birthdate[0],
    'year' => $birthdate[2], 
  );

  $form['filter']['birthdate'] = array(
    '#type' => 'date',
    '#title' => t('Birthdate'),
    '#description' => t('Date of birth of the user'),
    '#default_value' => $birthdate_format,
  );

  $form['filter']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#description' => t('User city'),
    '#required' => TRUE,
    '#default_value' => $data_user['city'],
  );

  $form['filter']['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#description' => t('User phone'),
    '#required' => TRUE,
    '#default_value' => $data_user['phone'],
    '#element_validate' => array('element_validate_number'),
  );

  $form['filter']['address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#description' => t('User address'),
    '#required' => TRUE,
    '#default_value' => $data_user['address'],
  );


  // Create a container for our buttons
  $form['buttons'] = array(
    '#type' => 'container',
  );

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update')
  );

  return $form;
}

/**
 * Submit editar usuario
 */
function sainet_edit_person_form_submit($form, &$form_state) {
  
  $values = $form_state['values'];

  $birthdate = $values['birthdate'];
  $birthdate_format = $birthdate['day'] . '/' . $birthdate['month'] . '/' . $birthdate['year'];

  // actualizando informacion del usuario
  $updated_user = db_update('sainet_register') 
    ->fields(array(
      'name' => $values['name'],
      'last_name' => $values['last_name'],
      'genre' => $values['genre'],
      'birthdate' => $birthdate_format,
      'city' => $values['city'],
      'phone' => $values['phone'],
      'address' => $values['address'],
    ))
    ->condition('id_sr', $values['id_user'], '=')
    ->execute();

  if ($updated_user) {
    drupal_set_message(t('Successfully updated user.'));
  }else {
    form_set_error(t('There was an error updating the user, try later.'));
  }      
}

/*
 * Retorna la informacion del o todos los usuarios
 */
function _sainet_get_full_data_user($id_user = NULL) {

  $query = db_select('sainet_register', 'sr');

  // consultar usuario especifico
  if ($id_user != NULL) {
    $result = $query
    ->fields('sr')
    ->condition('id_sr', $id_user,'=')
    ->execute()
    ->fetchAssoc();
    
    return $result;

  }else {
    // consultar todos los usuarios
    $sort = 'DESC';
    $order = ' send_date';

    $result = $query
    ->fields('sr')
    ->orderBy($order, $sort)
    ->execute();

    $rows = array();

    while($record = $result->fetchAssoc()) {
      $rows[] = $record;
    }
    return $rows;
  }
}


/**
 * Callback management/delete-person/%
 */
function sainet_delete_person($id_user) {
  $user_delete = db_delete('sainet_register')
  ->condition('id_sr', $id_user)
  ->execute();

  if ($user_delete) {
    drupal_set_message(t('User deleted successfully.'));
  }else {
    form_set_error(t('There was an error deleting the user, please try later.'));
  }

  drupal_goto('management/list-person');
}

/**
 * Callback management/report
 */
function sainet_report() {

  header('Content-type: application/vnd.ms-excel');
  header("Content-Disposition: attachment; filename=reporte-usuarios.xls");
  header("Pragma: no-cache");
  header("Expires: 0");
  echo '<table border=1> ';
  echo '<tr> ';
    echo '<th>' . t('Shipping ID') . '</th> ';
    echo '<th>' . t('Date of shipment') . '</th> ';
    echo '<th>' . t('Name') . '</th> ';
    echo '<th>' . t('Last Name') . '</th> ';
    echo '<th>' . t('Genre') . '</th> ';
    echo '<th>' . t('Birthdate') . '</th> ';
    echo '<th>' . t('City') . '</th> ';
    echo '<th>' . t('Phone') . '</th> ';
    echo '<th>' . t('Address') . '</th> ';
  echo '</tr> ';

  $rows = _sainet_get_full_data_user();

  foreach ($rows as $key => $value) {
      echo '<tr> ';
        echo '<td>' . $value['id_sr'] . '</td> ';
        echo '<td>' . $value['send_date'] . '</td> ';
        echo '<td>' . $value['name'] . '</td> ';
        echo '<td>' . $value['last_name'] . '</td> ';
        echo '<td>' . $value['genre'] . '</td> ';
        echo '<td>' . $value['birthdate'] . '</td> ';
        echo '<td>' . $value['city'] . '</td> ';
        echo '<td>' . $value['phone'] . '</td> ';
        echo '<td>' . $value['address'] . '</td> ';
      echo '</tr> ';

  }
  echo '</table> ';



}



