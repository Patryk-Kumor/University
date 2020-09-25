class AddNamesToBooking < ActiveRecord::Migration[5.2]
  def change
    add_column :bookings, :user_name, :string
    add_column :bookings, :product_name, :string
  end
end
