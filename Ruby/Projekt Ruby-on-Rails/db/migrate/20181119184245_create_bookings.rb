class CreateBookings < ActiveRecord::Migration[5.2]
  def change
    create_table :bookings do |t|
      t.integer :user_id
      t.integer :product_id
      t.datetime :start_date
      t.datetime :end_date
      t.boolean :returned

      t.timestamps
    end
  end
end
