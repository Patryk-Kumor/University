ActiveAdmin.register_page 'Dashboard' do
  menu priority: 1, label: proc { I18n.t('active_admin.dashboard') }

  content title: proc { I18n.t('active_admin.dashboard') } do
    columns do
      panel 'Actions' do
        ul do
          li link_to('Add product', new_product_path)
          li link_to('All products', products_path)
          li link_to('All users', users_path)
          li link_to('Reported comments', comments_reported_path)
          li link_to('Bookings', bookings_path)
        end
      end
    end
  end
end
