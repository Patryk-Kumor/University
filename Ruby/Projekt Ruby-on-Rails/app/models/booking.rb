class Booking < ApplicationRecord
  belongs_to :user, optional: true
  belongs_to :product

  def display_status
    return true if returned?

    end_date
  end
end
