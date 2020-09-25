class Product < ApplicationRecord
  include ActionView::Helpers::NumberHelper
  include PgSearch
  pg_search_scope :search, against: :name,
                           using: {
                             tsearch: { prefix: true, dictionary: 'english' }
                           }
  validates :name, :price, :category, :amount, presence: true
  validates :name, uniqueness: true
  validates :amount, :price, numericality: { greater_than_or_equal_to: 0 }
  has_many :comments
  has_many :bookings
  has_one_attached :picture
  attr_accessor :remove_picture
  after_save :purge_picture, if: :remove_picture

  def display_price
    price if price.positive?
  end

  def display_in_pln
    number_to_currency(price, locale: :pl) + ' PLN'
  end

  private

  def purge_picture
    picture.purge_later
  end
end
