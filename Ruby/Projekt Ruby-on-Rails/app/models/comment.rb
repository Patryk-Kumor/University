class Comment < ApplicationRecord
  belongs_to :product
  belongs_to :user, optional: true

  validates_presence_of :content
end
