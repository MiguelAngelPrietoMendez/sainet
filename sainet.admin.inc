<?php

/**
 * @file tbo_change_number.admin.inc
 */

/**
 * - Creando formulario para administrar servicios "changeNumberList" y "getAvailableNumberList" 
 * - Callback from "admin/config/tbo/settings-change-number"
 */
/*
function tbo_change_number_settings_form($form, &$form_state) {
  
  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings Change Number'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['fieldset']['tbo_change_number_many_numbers_show'] = array(
    '#title' => t("Many Numbers Show"),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tbo_change_number_many_numbers_show', 5),
    '#element_validate' => array('element_validate_number'),
  );

  $form['fieldset']['tbo_change_number_id_node_terms'] = array(
    '#title' => t("Node id terms and conditions"),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tbo_change_number_id_node_terms'),
    '#element_validate' => array('element_validate_number'),
  );

  $form['fieldset']['set_value'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set Value'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['fieldset']['set_value']['tbo_change_number_value_transaction'] = array(
    '#title' => t("Value of the Transaction"),
    '#description' => t('Leave 0 if the transaction has no value'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tbo_change_number_value_transaction', '0'),
  );
  $form['fieldset']['set_value']['tbo_change_number_period_number_change'] = array(
    '#title' => t("Period Number Change (Days)"),
    '#description' => t('Dndicate the number of days between the period of time between a number change'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tbo_change_number_period_number_change', 30),
  );

  $form['fieldset']['set_email'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set Email'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['fieldset']['set_email']['tbo_change_number_email_issue'] = array(
    '#title' => t("Email Issue"),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tbo_change_number_email_issue', 'Change Line Number'),
  );
  $form['fieldset']['set_email']['tbo_change_number_email_success'] = array(
    '#title' => t("Email Success"),
    '#type' => 'textarea',
    '#rows' => 4,
    '#cols' => 40,
    '#resizable' => FALSE,
    '#default_value' => variable_get('tbo_change_number_email_success', 'La transacción realizada término de manera exitosa. El número antiguo [msisdn:old_msisdn] fue cambiado por el siguiente número nuevo [msisdn:new_msisdn]'),
    '#description' => t('You may use these tokens: [msisdn:old_msisdn] y [msisdn:new_msisdn] of token "Msisdn"'),
  );
  $form['fieldset']['set_email']['tbo_change_number_email_failed'] = array(
    '#title' => t("Email Failed"),
    '#type' => 'textarea',
    '#rows' => 4,
    '#cols' => 40,
    '#resizable' => FALSE,
    '#default_value' => variable_get('tbo_change_number_email_failed', 'La transacción realizada fallo'),
    '#description' => t('You may use these tokens: {old_number} {new_number}'),
  );

  // --- Llamando el modulo "Token" para trabajar con los tokens
  // --- del "Msisdn" creados en "tbo_change_number.module -> tbo_change_number_token_info()"
  $form['fieldset']['set_email']['token_tree'] = array(
    '#theme' => 'token_tree',
  );

  $form['fieldset']['texts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Texts'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['fieldset']['texts']['tbo_change_number_instructive_text'] = array(
    '#title' => t("Instructional Text"),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tbo_change_number_instructive_text', 'Instructional Text'),
  );
  $form['fieldset']['texts']['tbo_change_number_without_cost'] = array(
    '#title' => t("Transaction without cost"),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tbo_change_number_without_cost', 'El cambio de número no tiene ningun costo'),
  );
  $form['fieldset']['texts']['tbo_change_number_transaction_cost'] = array(
    '#title' => t("Transaction cost"),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tbo_change_number_transaction_cost', 'El cambio de número tiene un costo de [texts:value]'),
  );


  

  return system_settings_form($form);
}
*/