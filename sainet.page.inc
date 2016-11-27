<?php

/**
 * Implements hook_form().
 *  Callback register/person
 */
function sainet_register_form($form, &$form_state) {

	// iniciar o continuar paso de formulario
  $form_state['step'] = isset($form_state['step']) ? $form_state['step'] : 1;
 
  $form['#prefix'] = '<div id="wrap-form-register">';
  $form['#suffix'] = '</div>';

  $function_step = '_sainet_register_step_' . $form_state['step'] . '_form';
  $function_step($form, $form_state);
  
  // Create a container for our buttons
  $form['buttons'] = array(
    '#type' => 'container',
  );

  // boton atras
  if($form_state['step'] !== 1) {
    $form['buttons']['back'] = array(
      '#type' => 'submit',
      '#value' => t('Back'),
      '#limit_validation_errors' => array(),
      '#submit' => array('sainet_register_form_back_submit'),
      '#ajax' => array(
        'wrapper' => 'wrap-form-register',
        'callback' => 'sainet_register_form_ajax_callback',
      ),
    );
  }

  // boton siguiente
  if($form_state['step'] !== 2) {
    $form['buttons']['forward'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      '#ajax' => array(
        'wrapper' => 'wrap-form-register',
        'callback' => 'sainet_register_form_ajax_callback',
      ),
    );
  }else {

  	// boton submit al formulario
    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      '#ajax' => array(
        'wrapper' => 'wrap-form-register',
        'callback' => 'sainet_register_form_ajax_callback',
      ),
    );
  }
 
  return $form;
}


/*
 * campos de formulario paso 1
 */
function _sainet_register_step_1_form(&$form, &$form_state) {

  $df_name      = '';
  $df_last_name = '';
  $df_genre     = 'woman';
  $df_birthdate = array('day' => 1, 'month' => 1, 'year' => 2012);

  if(isset($form_state['values']['name']) && isset($form_state['values']['last_name']) && isset($form_state['values']['genre']) && isset($form_state['values']['birthdate'])) {

    $df_name      = $form_state['values']['name'];
    $df_last_name = $form_state['values']['last_name'];
    $df_genre     = $form_state['values']['genre'];
    $df_birthdate = $form_state['values']['birthdate'];

  }else if(isset($form_state['storage']['name']) && isset($form_state['storage']['last_name']) && isset($form_state['storage']['genre']) && isset($form_state['storage']['birthdate'])) {
    
    $df_name      = $form_state['storage']['name'];
    $df_last_name = $form_state['storage']['last_name'];
    $df_genre     = $form_state['storage']['genre'];
    $df_birthdate = $form_state['storage']['birthdate'];
  }

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('User names'),
    '#required' => TRUE,
    '#default_value' => $df_name,
  );

  $form['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#description' => t('Surname of the user'),
    '#required' => TRUE,
    '#default_value' => $df_last_name,
  );

  $options_genre = array(
    t('Woman') => t('Woman'),
    t('Man') => t('Man'),
  );
  $form['genre'] = array(
    '#title' => t('Genre'),
    '#description' => t('Sex of the user'),
    '#type' => 'select',
    '#options' => $options_genre,
    '#default_value' => $df_genre,
    '#required' => TRUE,
  );

  $form['birthdate'] = array(
    '#type' => 'date',
    '#title' => t('Birthdate'),
    '#description' => t('Date of birth of the user'),
    '#default_value' => $df_birthdate,
  );

  return $form;
}


/*
 * campos de formulario paso 2
 */
function _sainet_register_step_2_form(&$form, &$form_state) {

  $df_city    = '';
  $df_phone   = '';
  $df_address = '';
  
  if(isset($form_state['values']['city']) && isset($form_state['values']['phone']) && isset($form_state['values']['address'])) {

    $df_city    = $form_state['values']['city'];
    $df_phone   = $form_state['values']['phone'];
    $df_address = $form_state['values']['address'];

  }else if(isset($form_state['storage']['city']) && isset($form_state['storage']['phone']) && isset($form_state['storage']['address'])) {
    
    $df_city    = $form_state['storage']['city'];
    $df_phone   = $form_state['storage']['phone'];
    $df_address = $form_state['storage']['address'];
  }

  $form['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#description' => t('User city'),
    '#required' => TRUE,
    '#default_value' => $df_city,
  );

  $form['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#description' => t('User phone'),
    '#required' => TRUE,
    '#default_value' => $df_phone,
    '#element_validate' => array('element_validate_number'),
  );

  $form['address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#description' => t('User address'),
    '#required' => TRUE,
    '#default_value' => $df_address,
  );

  
  return $form;
}
 

/*
 * Callback boton atras
 */
function sainet_register_form_back_submit($form, &$form_state) {
  $form_state['step']--;
  $form_state['rebuild'] = TRUE;
}
 

/*
 * Submit formulario registro
 */
function sainet_register_form_submit($form, &$form_state)
{
  
  $step = $form_state['step'];

  switch ($step) {
    case 1:
      $form_state['storage']['name']      = $form_state['values']['name'];
      $form_state['storage']['last_name'] = $form_state['values']['last_name'];
      $form_state['storage']['genre']     = $form_state['values']['genre'];
      $form_state['storage']['birthdate'] = $form_state['values']['birthdate'];
      break;

    case 2:
      $form_state['storage']['city']    = $form_state['values']['city'];
      $form_state['storage']['phone']   = $form_state['values']['phone'];
      $form_state['storage']['address'] = $form_state['values']['address'];
      break;
  }
 
 	// si se dio clic en boton siguiente
  if(isset($form_state['values']['forward']) && $form_state['values']['op'] == $form_state['values']['forward']) {
    $form_state['step']++;
  }
  // si se dio clic submit al formulario de registro
  elseif(isset($form_state['values']['submit']) && $form_state['values']['op'] == $form_state['values']['submit']) {

    $birthdate = $form_state['storage']['birthdate'];
    $birthdate_format = $birthdate['day'] . '/' . $birthdate['month'] . '/' . $birthdate['year'];

    // guardando usuario en la db
    $insert_user = db_insert('sainet_register') 
      ->fields(array(
        'send_date' => date("Y-m-d h:i:s"),
        'name' => $form_state['storage']['name'],
        'last_name' => $form_state['storage']['last_name'],
        'genre' => $form_state['storage']['genre'],
        'birthdate' => $birthdate_format,
        'city' => $form_state['storage']['city'],
        'phone' => $form_state['storage']['phone'],
        'address' => $form_state['storage']['address'],
      ))
      ->execute();

    if ($insert_user) {
      unset($form_state['storage']['birthdate']);
      $items = $form_state['storage'];
      array_push($items, $birthdate_format);

      drupal_set_message(t('You have successfully registered, with the following data:!values', array('!values' => theme('item_list', array('items' => $items)))));
    }else {
      form_set_error(t('An error occurred while registering the user, try later.'));
    }      

    // retornando al paso 1 del formulario de registro
    $form_state['step'] = 1;
    $form_state['storage'] = array();
  }
 
  $form_state['rebuild'] = TRUE;
}
 

function sainet_register_form_ajax_callback($form, &$form_state) {
  return $form;
}


/*
 * Implements hook_form().
 * Callback management/list-person
 */
function sainet_list_person_form($form, &$form_state) {

	//titulos
	$header = array(
    array('data' => t('Shipping ID'),'field' => 'id_sr'),
    array('data' => t('Date of shipment'),'field' => 'send_date'),
    array('data' => t('Name'),'field' => 'name'),
    array('data' => t('Last Name'),'field' => 'last_name'),
    array('data' => t('Genre'),'field' => 'genre'),
    array('data' => t('Birthdate'),'field' => 'birthdate'),
    array('data' => t('City'),'field' => 'city'),
    array('data' => t('Phone'),'field' => 'phone'),
    array('data' => t('Address'),'field' => 'address'),
    array('data' => t('Operations'),'field' => 'operations'),
  );

	// Ordenar por columnas
	if(isset($_GET['sort']) && isset($_GET['order'])){
	  if($_GET['sort'] == 'asc')
	    $sort = 'ASC';
	  else
	    $sort = 'DESC';
	   switch($_GET['order']){
	     case 'Shipping ID':
	       $order = 'id_sr';
	       break;
	     default:
	       $order = 'send_date';
	   }
	 }
	 else {
	   $sort = 'DESC';
	   $order = ' send_date';
	 }


	// Consultando db con o sin filtros
	$query = db_select('sainet_register', 'sr');

	if (isset($form_state['filters']['date_from']) && isset($form_state['filters']['date_to'])) {

		$query->condition('send_date', $form_state['filters']['date_from'], '>');
		$query->condition('send_date', $form_state['filters']['date_to'], '<=');
	  //$query->condition('sr.send_date', array($form_state['filters']['date_from'], $form_state['filters']['date_to']), 'BETWEEN');
	}
	if (isset($form_state['filters']['genre']) && !empty($form_state['filters']['genre'])) {
	  $query->condition('genre', '%' . db_like($form_state['filters']['genre']) . '%', 'LIKE');
	}
	if (isset($form_state['filters']['name']) && !empty($form_state['filters']['name'])) {
	  
	  $db_or = db_or();
    $db_or->condition('name', '%' . db_like($form_state['filters']['name']) . '%', 'LIKE');
    $db_or->condition('last_name', '%' . db_like($form_state['filters']['name']) . '%', 'LIKE');
    
	  $query->condition($db_or);

	}

  $result = $query
    ->fields('sr')
    ->orderBy($order, $sort)
    ->extend('TableSort')->extend('PagerDefault')->limit(50)
    ->execute();
    //->fetchAssoc();
 

  // filtros
 	$form = array();
 
	$form['filter'] = array(
	  '#type' => 'fieldset',
	  '#collapsible' => TRUE,
	  '#collapsed' => TRUE,
	  '#title' => t('Filter option')
	);

	$form['filter']['range'] = array(
	  '#type' => 'fieldset',
	  '#collapsible' => TRUE,
	  '#collapsed' => FALSE,
	  '#title' => t('Filter Range')
	);
	$form['filter']['range']['date_from'] = array(
    '#type' => 'date',
    '#title' => t('From'),
    '#size' => 20,
  );
  $form['filter']['range']['date_to'] = array(
    '#type' => 'date',
    '#title' => t('To'),
    '#size' => 20,
  );

	$form['filter']['genre'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Genre'),
	  '#size' => 20,
	);
	$form['filter']['name'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Name and last name'),
	  '#size' => 30,
	);

	$form['filter']['submit'] = array(
	  '#type' => 'submit',
	  '#value' => t('Filter'),
	);

	// rows de la tabla
	$rows = array();
  foreach ($result as $ord) {
    $rows[] = array(
    	$ord->id_sr,
    	$ord->send_date,
    	$ord->name,
    	$ord->last_name,
    	$ord->genre,
    	$ord->birthdate,
    	$ord->city,
    	$ord->phone,
    	$ord->address,
    	l(t('Edit'), 'management/edit-person/'. $ord->id_sr) . ' - ' . l(t('Delete'), 'management/delete-person/'. $ord->id_sr),
    );
  }
    
  $form['table'] = array(
	  '#theme' => 'table',
	  '#header' => $header,
	  '#rows' => $rows,
	  '#empty' => t('Table has no row!')
	);

  // paginador de la tabla
  $form['pager'] = array('#markup' => theme('pager'));

  // export de usuarios
  $form['export'] = array(
	  '#markup' => l(t('Download Report xls'), 'management/report'),	
  );

  return $form;
}

/*
 * Callback filtro de tabla
 */
function sainet_list_person_form_submit($form, &$form_state) {

	$values = $form_state['values'];

	$from = $values['date_from'];
  $from_format = $from['year'] . '-' . $from['month'] . '-' . $from['day'] . ' 00:00:00';

  $to = $values['date_to'];
  $to_format = $to['year'] . '-' . $to['month'] . '-' . $to['day'] . ' 23:59:59';

  $form_state['filters']['date_from'] = $from_format;
  $form_state['filters']['date_to']   = $to_format;
  $form_state['filters']['genre']     = $values['genre'];
  $form_state['filters']['name']      = $values['name'];

  $form_state['rebuild'] = TRUE;
}
